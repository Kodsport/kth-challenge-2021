#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<string> notes = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};
vector<bool> incidental;

int NOTES = sz(notes);

ll tonote(string note) {
  string octave;
  if (note[1] == '#') {
    octave = note.substr(2, sz(note) - 2);
  } else {
    octave = note.substr(1, sz(note) - 1);
  }
  note = note.substr(0, sz(note) - sz(octave));
  int thenote = (int)(find(all(notes), note) - notes.begin());
  int oct = stoi(octave);
  return ll(oct) * NOTES + thenote;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
  for (auto& it : notes) {
    incidental.push_back(sz(it) == 2);
  }
  
  int N;
  cin >> N;
  string lo, hi;
  cin >> lo >> hi;
  ll lonote = tonote(lo);
  ll hinote = tonote(hi);

  vector<int> counts(NOTES);
  ll lowest = 1e11, highest = 0;
  rep(i,0,N) {
    string str;
    cin >> str;
    ll note = tonote(str);
    lowest = min(lowest, note);
    highest = max(highest, note);
    counts[note % NOTES]++;
  }

  vector<ll> incidentals(NOTES);
  rep(shift,0,NOTES) {
    rep(i,0,NOTES) {
      int note = (shift + i) % NOTES;
      if (incidental[note]) {
        incidentals[shift] += counts[i];
      }
    }
  }
  cerr << "interval: " << lonote << " " << hinote << endl;
  cerr << "song interval is " << lowest << " " << highest << endl;

  ll ans = 0;
  ll best = N;
  rep(shift,0,NOTES) {
    if (incidentals[shift] > best) continue;
    cerr << "shifting with " << shift << " is ok" << endl;
    // lonote <= lowest + 11X + shift <=> lonote - lowest - shift <= 11X
    // highest + 11X + shift <= hinote <=> 11X <= hinote - shift - highest
    ll left = lonote - lowest - shift;
    ll right = hinote - highest - shift;
    if (left > right) continue;

    cerr << "left adjusted " << left << " right adjusted " << right << endl;
    left = (left + NOTES - 1) / NOTES * NOTES;
    right = right / NOTES * NOTES;
    cerr << "left rounded " << left << " right rounted " << right << endl;
    if (left > right) continue;
    if (incidentals[shift] < best) {
        ans = 0;
        best = incidentals[shift];
    }
    ans += (right - left) / NOTES + 1;
  }
  cout << best << " " << ans << endl;
}
