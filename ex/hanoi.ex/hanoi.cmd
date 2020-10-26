HOW TO HANOI n:
   INITIALISE
   FOR i IN {1..(2**n)-1}:
      SELECT.PROCESS
      WRITE 'Move piece', piece, 'from', from, 'to', to /
      RE.SCHEDULE
INITIALISE:
   PUT {} IN process
   FOR i IN {1..n}:
      INSERT 2**(i-1), i, 1, (-1)**(i+n), 2**i IN process
SELECT.PROCESS:
   PUT min process IN time, piece, from, direction, wait
   REMOVE min process FROM process
RE.SCHEDULE:
   INSERT time+wait, piece, to, direction, wait IN process
to:
   RETURN ((from+direction-1) mod 3) + 1
