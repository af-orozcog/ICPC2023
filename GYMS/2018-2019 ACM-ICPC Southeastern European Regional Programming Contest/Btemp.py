n = int(input())

ans = 0
imp = n//2
for i in range(1,imp):
    ans += (i+1)*(imp-i)

ans += (imp*(imp+1))//2

print(ans)