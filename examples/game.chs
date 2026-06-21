num hp = 100
num turn = 0
while hp > 0
    num dmg = turn * 20 + 10
    hp = hp - dmg
    print(hp)
    turn = turn + 1
end while
print("Game Over!")
