killall afplay

echo "Let the funk begin"

number = $RANDOM
let "number %= 4"
if ["$number" -eq 0]
then
    afplay /usr/local/include/song.mp3 &
elif ["$number" -eq 1]
then
    afplay /usr/local/include/song3.mp3 &
elif ["$number" -eq 2]
then
    afplay /usr/local/include/song4.mp3 &
else
    afplay /usr/local/include/song5.mp3 &
fi

vim
