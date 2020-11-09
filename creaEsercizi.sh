#!/bin/bash

data=`date +%s`
test_ly_name="test_$data.ly"
solution_ly_name="solution_$data.ly"
test_pdfName="esercizio"
solution_pdfName="soluzione"

numeroNote=`printf "%d" $1`
numeroNote=$(( numeroNote + 0 ))

if ((numeroNote == 0)); then
  echo "Syntax: $0 numeroNote" 
  exit -1
fi

cat > $test_ly_name << @EOF
% Default layout:

\layout {
  indent = #0
  line-width = #180 % #150
  ragged-last = ##t
}

<<
  \new Staff \with { \omit TimeSignature } \new Voice = melody {
    \hide KeySignature
    \hide Stem
@EOF

cp $test_ly_name $solution_ly_name

cat >> $test_ly_name << @EOF
    \hide NoteHead
@EOF

# Only solutions
nota="d' "
for ((i=0; i<numeroNote; i=i+1)); do
  echo -n "$nota" >> $test_ly_name
  nota="d' "
  if ((i % 4 == 0)); then
          echo "" >> $test_ly_name
  fi
done
echo "" >> $test_ly_name

# Only exercize
./generaNote $numeroNote $data 2 note >> $solution_ly_name

testo=`./generaNote $numeroNote $data 2 name`

cat >> $test_ly_name << @EOF
  }
  \new Lyrics \lyricsto melody { $testo }
>>
@EOF

cat >> $solution_ly_name << @EOF
  }
  \new Lyrics \lyricsto melody { $testo }
>>
@EOF

lilypond -o "$test_pdfName" "$test_ly_name"
lilypond -o "$solution_pdfName" "$solution_ly_name"
rm -f "$test_ly_name" "$solution_ly_name"

evince "$test_pdfName.pdf" "$solution_pdfName.pdf" &

