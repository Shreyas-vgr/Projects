s2=" "+raw_input("Enter Source String : ")
s1=" "+raw_input("Enter Target String : ")
m=len(s1)
n=len(s2)
p=list([0]*n)
edit=[]
paths=[]

def illustrate(path):
    a1=""
    a2=""
    i=1
    j=1
    c=0
    while  c <len(path):
        if path[c]=='NC' or path[c]=='SUB':
            a1+=s1[i]
            a2+=s2[j]
            i+=1
            j+=1
        if path[c]=='DEL':
            a2+=s2[j]
            a1+=" "
            j+=1
        if path[c]=='INS':
            a1+=s1[i]
            a2+=" "
            i+=1
        c+=1
    print a2
    print a1



def path_trav(i,j,path):
    global paths
    if i+j==0:
        paths.append(path[:])
        return
    if s1[i]==s2[j]:
        if edit[i][j]==edit[i-1][j-1]:
            path=["NC"]+path
            path_trav(i-1,j-1,path[:])
    else:
        if edit[i][j]==edit[i-1][j-1]+1:
            path=["SUB"]+path
            path_trav(i-1,j-1,path[:])
    if edit[i][j]==edit[i-1][j]+1:
        path=["INS"]+path
        path_trav(i-1,j,path[:])
    if edit[i][j]==edit[i][j-1]+1:
        path=["DEL"]+path
        path_trav(i,j-1,path[:])


for i in range(m):
    edit.append(list(p))
for j in range(n):
    edit[0][j]=j
for i in range(1,m):
    edit[i][0]=i
    for j in range(1,n):
        #print edit
        if s1[i]==s2[j]:
            edit[i][j]=min([edit[i-1][j]+1,edit[i][j-1]+1,edit[i-1][j-1]])
        else:
            edit[i][j]=min([edit[i-1][j]+1,edit[i][j-1]+1,edit[i-1][j-1]+1])

for i in range(m):
    print edit[i]
print "Levensthein Distance For the given strings : ",edit[m-1][n-1]
path_trav(m-1,n-1,[][:])
#   print paths
s1+=" "*m
s2+=" "*m
l=1
for i in paths:
    print l
    l+=1
    illustrate(i)
