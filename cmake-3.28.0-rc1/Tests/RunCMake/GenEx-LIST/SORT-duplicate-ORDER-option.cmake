
file(GENERATE OUTPUT result.txt CONTENT "$<LIST:SORT,a;b,ORDER:ASCENDING,COMPARE:STRING,ORDER:DESCENDING,CASE:SENSITIVE>")
