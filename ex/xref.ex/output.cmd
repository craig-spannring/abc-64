HOW TO OUTPUT xtab:
   FOR word IN keys xtab:
      WRITE word<<10
      FOR line IN xtab[word]:
         WRITE line>>4, ' '
      WRITE /
