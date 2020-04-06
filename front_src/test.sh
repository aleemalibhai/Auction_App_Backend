# run compiled program for all inputs
# write outputs to output folder
for file in test_cases/input/*; do
  outfile="test_cases/output/actual/${file##*/}"
	timeout 10 ./Auction_app resources/users.txt resources/items.txt resources/daily_transactions.txt < $file > $outfile

done

#check difference between expected and actual
rep="test_cases/output/report.txt"
> $rep

for file1 in test_cases/output/actual/*; do
  file2="test_cases/output/expected/${file1##*/}"
  diffFile="test_cases/output/differences/${file1##*/}"

  output=$(diff -u $file1 $file2)


  if [[ $output ]]; then
    echo "${file1##*/}:  Failed" >> $rep
  else
    echo "${file1##*/}:  Passed" >> $rep
  fi

done

