HOW TO ANALYZE line:
   SHARE followers, starters, enders
   IF #line>2:
      PUT line item 1, line item 2 IN c1, c2
      INSERT c1, c2 IN starters
      INSERT line@#line IN enders
      FOR c3 IN line@3:
         IF (c1, c2) not.in keys followers:
            PUT {} IN followers[c1,c2]
         INSERT c3 IN followers[c1, c2]
         PUT c2, c3 IN c1, c2
