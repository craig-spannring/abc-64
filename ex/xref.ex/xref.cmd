HOW TO XREF text:
   SHARE xtab
   PUT {} IN xtab
   FOR line IN keys text:
      TREAT.LINE
   OUTPUT xtab
TREAT.LINE:
   FOR word IN words text[line]:
      SAVE word AT line
