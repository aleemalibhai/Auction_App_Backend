# run the daily transaction file multiple times
inputFolder=$1

for folder in $inputFolder; do
  echo $folder 
  timeout 10 ./sim_day.sh $folder
done

