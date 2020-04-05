currentDate=`date +%s`
inputDirectory=$1
outFile="sim/mergedTransactionFile.txt"

# clear merged transaction file
>$outFile 

for file in $inputDirectory; do
  while IFS= read -r line
  do
    # skip if end of session
    if [&{line:0:2} -ne "00"]
        echo line >> $outFile
    fi
  done <"$file"

done

# remove old transaction files
rm $inputDirectory/*

