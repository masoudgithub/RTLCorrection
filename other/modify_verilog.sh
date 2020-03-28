#bash script for editting .v file created by LegUp to be read by yosys
awk '{gsub(/\$finish;/,"/*$finish;*/")}1' $1 > temp.v && mv temp.v $1
awk '{gsub(/\@\(negedge clk\);/,"/*@(negedge clk);*/")}1' $1 > temp.v && mv temp.v $1
