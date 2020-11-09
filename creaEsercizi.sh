#!/bin/bash

data=`date +%s%N`
test_ly_name="test_$data.ly"
solution_ly_name="solution_$data.ly"
test_pdfName="esercizio"
solution_pdfName="soluzione"
all_pdfName="esercizio_soluzione"

numeroNote=`printf "%d" $1`
numeroNote=$(( numeroNote + 0 ))

if ((numeroNote == 0)); then
  numeroNote=360
fi

cat > $test_ly_name << @EOF
% Default layout:

\header {
  tagline = "Esercizio di scrittura di note generato il `date +%d.%m.%Y` alle `date +%H:%M`"  % removed
}

\layout {
  indent = #0
  line-width = #180 % #150
  ragged-last = ##t
}

\paper {
  bottom-margin = 1\cm
}

<<
  \new Staff \with { \omit TimeSignature } \new Voice = melody {
    \hide KeySignature
    \hide Stem
@EOF

cp $test_ly_name $solution_ly_name
sed -e "s/Esercizio/Solutione all'esercizio/g" -i $solution_ly_name

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
  \new Lyrics \lyricsto melody {
  \override LyricText.font-name = #"Source Serif Pro"
%  \override LyricText.font-name = #"Equity Text A"
%  \override LyricText.font-name = #"Sunday Comics BB"
  \override LyricText.font-size = #-2 
$testo }
>>
@EOF

cat >> $solution_ly_name << @EOF
  }
  \new Lyrics \lyricsto melody {
  \override LyricText.font-name = #"Source Serif Pro"
%  \override LyricText.font-name = #"Equity Text A"
%  \override LyricText.font-name = #"Sunday Comics BB"
  \override LyricText.font-size = #-2
$testo }
>>
@EOF

lilypond -o "$test_pdfName" "$test_ly_name"
lilypond -o "$solution_pdfName" "$solution_ly_name"
# rm -f "$test_ly_name" "$solution_ly_name"

# evince "$test_pdfName.pdf" "$solution_pdfName.pdf" &
pdftk "$test_pdfName.pdf" "$solution_pdfName.pdf" cat output "$all_pdfName.pdf"
rm -f "$test_pdfName.pdf" "$solution_pdfName.pdf"
evince "$all_pdfName.pdf"

