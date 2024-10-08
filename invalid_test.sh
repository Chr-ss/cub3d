path=./maps/invalid
exe=./cub3D

RED="\x1B[31m"
GRN="\x1B[1;32m"
YEL="\x1B[33m"
BLU="\x1B[34m"
MAG="\x1B[35m"
BMAG="\x1B[1;35m"
CYN="\x1B[36m"
BCYN="\x1B[1;36m"
WHT="\x1B[37m"
RESET="\x1B[0m"
LINEP="\033[75G"

maps=$(find $path -name "*" | sort)

x=0
for map in $maps
do
x=$((x+1))
err_msg=$(timeout --preserve-status 0.1s $exe $map 2>&1 | tr -d '\n')
if [ -z "$err_msg" ];
then
err_msg="DID NOT FAIL"
echo -e "${RED}${x} : ${map} : ${err_msg}${RESET}"
else
echo -e "${GRN}${x} : ${map} : ${err_msg}${RESET}"
fi

done
