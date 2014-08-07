/* eval.c 35e */
/* Jake Austin and Ian Mcconnell, Impcore II */
#include "all.h"

/* eval helpers 40a */
/* Included local variable environment as parameter */
/* updated call to mkVL and eval */
static Valuelist evallist(Explist el, Valenv globals, Funenv functions, 
                                         Valenv formals, Valenv locals) {
    if (el == NULL) {
        return NULL;
    } else {
        Value v = eval(el->hd, globals, functions, formals, locals); 
        return mkVL(v, evallist(el->tl, globals, functions, formals, locals));
    }
}

/* eval.c 36a */
/* Included local variable environment as parameter in all calls to eval */
Value eval(Exp e, Valenv globals, Funenv functions, Valenv formals, 
                                                    Valenv locals) {
    checkoverflow(1000000 * sizeof(char *)); /* OMIT */
    switch (e->alt) {
    case LITERAL:
        /* evaluate [[e->u.literal]] and return the result 36b */
        return e->u.literal;
    case VAR:
        /* added locals as primary case, hides formals - globals */
        /* evaluate [[e->u.var]] and return the result 37a */
	if (isvalbound(e->u.var, locals))
	    return fetchval(e->u.var, locals);
	else if (isvalbound(e->u.var, formals))
            return fetchval(e->u.var, formals);
        else if (isvalbound(e->u.var, globals))
            return fetchval(e->u.var, globals);
        else
            error("unbound variable %n", e->u.var);
        assert(0);   /* not reached */
        return 0;   
    case SET:
	/* Local environment preferentially modified */
    {
            Value v = eval(e->u.set.exp, globals, functions, formals, locals);
	    if (isvalbound(e->u.set.name, locals))
		bindval(e->u.set.name, v, locals);
            else if (isvalbound(e->u.set.name, formals))
                bindval(e->u.set.name, v, formals);
            else if (isvalbound(e->u.set.name, globals))
                bindval(e->u.set.name, v, globals);
            else
                error("set: unbound variable %n", e->u.set.name);
            return v;
    }
    case IFX:
        /* evaluate [[e->u.ifx]] and return the result 38a */
        if (eval(e->u.ifx.cond, globals, functions, formals, locals) != 0)
            return eval(e->u.ifx.true, globals, functions, formals, locals);
        else
            return eval(e->u.ifx.false, globals, functions, formals, locals);
    case WHILEX:
        /* evaluate [[e->u.whilex]] and return the result 38b */
        while (eval(e->u.whilex.cond, globals, functions, formals, locals) != 0)
            eval(e->u.whilex.exp, globals, functions, formals, locals);
        return 0;
    case BEGIN:
        /* evaluate [[e->u.begin]] and return the result 39a */
        {
            Explist el;
            Value v = 0;
            for (el=e->u.begin; el; el=el->tl)
                v = eval(el->hd, globals, functions, formals, locals);
            return v;
        }
    case APPLY:
        /* Case USERDEF: create local environment to pass into eval */
        /* evaluate [[e->u.apply]] and return the result 39b */
        {
            Fun f;
            /* make [[f]] the function denoted by [[e->u.apply.name]], or call
                                                               [[error]] 39c */
            if (!isfunbound(e->u.apply.name, functions))
                error("call to undefined function %n", e->u.apply.name);
            f = fetchfun(e->u.apply.name, functions);
            switch (f.alt) {
            case USERDEF:
                /* apply [[f.u.userdef]] and return the result 40b */
                {
		    Namelist n2 = f.u.userdef.locals;
		    Valuelist v2 = NULL;
		    int i = 0;

                    Namelist  nl = f.u.userdef.formals;
                    Valuelist vl = evallist(e->u.apply.actuals, globals,
					    functions, formals, locals);
                    checkargc(e, lengthNL(nl), lengthVL(vl));
		    
		    
                    /* Initialize local values to 0 */
		    while (i < lengthNL(n2)) {
                            v2 = mkVL(0, v2);
			    i = lengthVL(v2);
		       
		    }
		    checkargc(e, lengthNL(n2), lengthVL(v2));
                    return eval(f.u.userdef.body, globals, functions, mkValenv(
				    nl, vl), mkValenv(n2, v2));
                }
            case PRIMITIVE:
                /* apply [[f.u.primitive]] and return the result 41a */
                {
                    Valuelist vl = evallist(e->u.apply.actuals, globals,
					    functions, formals, locals);
                    if (f.u.primitive == strtoname("print"))
                        /* apply [[print]] to [[vl]] and return 41b */
                        {
                            Value v;
                            checkargc(e, 1, lengthVL(vl));
                            v = nthVL(vl, 0);
                            print("%v\n", v);
                            return v;
                        }
                    else
                      /* apply arithmetic primitive to [[vl]] and return 42a */
                        {
                            const char *s;
                            Value v, w;

                            checkargc(e, 2, lengthVL(vl));
                            v = nthVL(vl, 0);
                            w = nthVL(vl, 1);

                            s = nametostr(f.u.primitive);
                            assert(strlen(s) == 1);
                            switch (s[0]) {
                            case '<':
                                return v < w;
                            case '>':
                                return v > w;
                            case '=':
                                return v == w;
                            case '+':
                                return v + w;
                            case '-':
                                return v - w;
                            case '*':
                                return v * w;
                            case '/':
                                if (w == 0)
                                    error("division by zero in %e", e);
                                return v / w;
                            default:
                                assert(0);
                                return 0;   /* not reached */
                            }
                        }
                }
            default:
                assert(0);
                return 0;   /* not reached */
            }
        }
    default:
        assert(0);
        return 0;   /* not reached */
    }
}
/* eval.c 42b */
void readevalprint(Defreader reader, Valenv globals, Funenv functions, int echo)                                                                              {
    Def d;
    while ((d = readdef(reader)))
        evaldef(d, globals, functions, echo);
}
/* eval.c 43a */
void evaldef(Def d, Valenv globals, Funenv functions, int echo) { 
    switch (d->alt) {
    case VAL:
        /* evaluate [[d->u.val]], mutating [[globals]] 43b */
	/* updated to correct number of parameters*/
       {
            Value v = eval(d->u.val.exp, globals, functions, mkValenv(NULL, NULL), mkValenv(NULL, NULL));
	    /*if in local environment, bind to locals*/
            bindval(d->u.val.name, v, globals);
            if (echo)
                print("%v\n", v);
        }
        break;
    case EXP:
        /* evaluate [[d->u.exp]] and possibly print the result 44a */
        {
            Value v = eval(d->u.exp, globals, functions,mkValenv(NULL,NULL), mkValenv(NULL, NULL));
            bindval(strtoname("it"), v, globals);
            if (echo)
                print("%v\n", v);
        }
        break;
    case DEFINE:
        /* evaluate [[d->u.define]], mutating [[functions]] 44b */
        /* fail if [[d->u.define]] has duplicate formal parameters 44c */
        if (duplicatename(d->u.define.userfun.formals) != NULL)
            error(
         "Formal parameter named %n appears twice in definition of function %n",
                  duplicatename(d->u.define.userfun.formals), d->u.define.name);
        bindfun(d->u.define.name, mkUserdef(d->u.define.userfun), functions);
        if (echo)
            print("%n\n", d->u.define.name);
        break;
    case USE:
        /* evaluate [[d->u.use]], possibly mutating [[globals]] and
                                                            [[functions]] 44d */
        {
            const char *filename = nametostr(d->u.use);
            FILE *fin = fopen(filename, "r");
            if (fin == NULL)
                error("cannot open file \"%s\"", filename);
            readevalprint(defreader(filereader(filename, fin), 0), globals,
                                                                  functions, 0);
            fclose(fin);
        }
        break;
    default:
        assert(0);
    }
}
