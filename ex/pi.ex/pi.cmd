HOW TO PI n':
   \Print the first n places of pi. a, b, c and d get very large.
   WRITE '3.'
   PUT n' IN n
   PUT 3, 0, 40, 4, 24, 0, 1 IN k, a, b, c, d, e, f
   WHILE n>0:
      WHILE e=f AND n>0:
         WRITE e<<1
         PUT n-1 IN n
         PUT 10*(a-e*c), 10*(b-f*d) IN a, b
         PUT floor(a/c), floor(b/d) IN e, f
      PUT k**2, 2*k+1, k+1 IN p, q, k
      PUT b, p*a+q*b, d, p*c+q*d IN a, b, c, d
      PUT f, floor(b/d) IN e, f
   WRITE /
