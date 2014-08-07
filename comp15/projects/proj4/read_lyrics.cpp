#include <iostream>
#include <fstream>

using namespace std;

void read_lyrics(char * filename)
{
  ifstream in(filename);

  int song_count = 0;

  // -- While more data to read...
  while ( ! in.eof() ) {

    // -- First line is the artist
    string artist;
    getline(in, artist);

    if (in.fail()) break;

    // -- Second line is the title
    string title;
    getline(in, title);

    if (in.fail()) break;

    song_count++;
    if (song_count % 10000 == 0) {
      cout << "At " << song_count << " Artist: " << artist << " Title:" << title << endl;
    }

    // -- Then read all words until we hit the special <BREAK> token
    bool done = false;
    string word;
    while ( ! done) {
      in >> word;
      if (word == "<BREAK>") {
	done = true;
      } else {
	// -- Found a word
      }
    }

    // -- Important: skip the newline left behind
    in.ignore();
  }
}
