#!/bin/bash

file=$1

if [[ $file == "" ]]; then {
  echo "runall.sh requires an input data filename, e.g.:"
  echo "  ./runall.sh uniform.data"
  exit 0
}; fi

for config in 1 2 3 4; do {
	./supermarket > ${file}.${config}.out <<EOF
$config
$file
EOF

	av=`grep '^ *[a-zA-Z]\+ *[0-9]\+ *[0-9]\+ *[0-9]\+' ${file}.${config}.out | awk 'BEGIN { s=0 } { s+=$4 } END { print s/NR; }'`
	xav=`grep '^ *[a-zA-Z]\+ *[0-9]\+ *[0-9]\+ *[0-9]\+' ${file}.${config}.out | awk 'BEGIN { s=0; c=0; } { if ($2 < 6) { s+=$4; c=c+1; } } END { print s/c; }'`

echo "Config $config: average wait $av, for express customers $xav"

}; done

