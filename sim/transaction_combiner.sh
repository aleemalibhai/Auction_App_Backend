currentDate=`date +%s`
inputDirectory=$1
outFile="sim/mergedTransactionFile.txt"


echo $outFile 

for file in $inputDirectory; do
  while IFS= read -r line
  do
    if [&{line:0:2} -ne "00"]
        echo line >> $outFile
    fi
  done <"$file"

done

