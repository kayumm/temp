
# sorting algorithm
# find the largest number in list

arr=(1 2 3 4 5)
echo ${arr[2]}
b=10
arr[2]=$((${arr[2]}+$b))

echo ${arr[2]}

for (( i=0; i<${#arr[@]}; i++ ))
do
    echo ${arr[$i]}
done

sum=0
for (( i=0; i<${#arr[@]}; i++ ))
do
    sum=$(($sum+${arr[$i]}))
done


Func() {
    echo 'hello function!'
}
Func

SumOfThree() {
    ss=$(($1+$2+$3))
    return $ss
}

SumOfThree 1 2 99
echo $?
sum=$?
echo $sum

a='hello'
b='hello'
if [[ $a == $b ]]
then
    echo 'correct'
fi




arr=(3 4 9 1 32 -11 22 9)
length=${#arr[@]}

# max elem
max=0
for (( i=0; i<$length; i++ ))
do
    if (( ${arr[$i]} > $max ))
    then
        max=${arr[$i]}
    fi
done
echo 'max value:' $max

# bubblesort
for (( i=0; i<$length; i++ ))
do
    for (( j=0; j<$length-i-1; j++ ))
    do
        if (( ${arr[j]} > ${arr[j+1]} ))
        then
            temp=${arr[j]}
            arr[j]=${arr[j+1]}
            arr[j+1]=$temp
        fi
    done
done
echo ${arr[@]}

bubblesort () {
    arr2=$1
    length=$2
    for (( i=0; i<length; i++ ))
    do
        for (( j=0 ; j<length-i-1; j++ ))
        do
            if (( ${arr[j]} > ${arr[j+1]} ))
            then
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done
    done
    return $arr2
}
bubblesort $arr $length
res=$?
echo ${arr[@]}

# searching for a string
mylst=('hello' 'world' 'hi' 'ewu' 'skyblue')
findString () {
    flag=0
    lst=$1
    word=$2
    # len=$3
    for i in ${lst[@]}
    do
        if [[ $word == ${lst[i]} ]]
        then
            echo 'item found!'
            flag=1
            break
        fi
    done
    if (( $flag == 0 ))
    then
        echo 'not found!'
    fi
}
wrd='hi'
len=${#mylst[@]}
findString mylst[@] $wrd

findString () {
    lst=(${!1})  # Indirect expansion of the array
    word=$2
    flag=0

    for item in "${lst[@]}"
    do
        if [[ "$word" == "$item" ]]
        then
            echo 'item found!'
            flag=1
            break
        fi
    done

    if (( flag == 0 ))
    then
        echo 'not found!'
    fi
}
# Example usage
mylst=('hello' 'world' 'hi')
wrd='hi'
findString mylst[@] $wrd

