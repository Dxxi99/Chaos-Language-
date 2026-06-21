import "math"

func attack(hp, damage)
    num newHp = hp - damage
    if newHp < 0
        newHp = 0
    end if
    return newHp
end func

func isDead(hp)
    if hp <= 0
        return 1
    end if
    return 0
end func

num heroHp = 100
num turn = 0

while turn < 5
    num dmg = turn * 20 + 10
    heroHp = attack(heroHp, dmg)
    print(heroHp)
    
    if isDead(heroHp)
        print("Dead!")
        turn = 5
    end if
    turn = turn + 1
end while

print(factorial(6))
print(abs(-99))
