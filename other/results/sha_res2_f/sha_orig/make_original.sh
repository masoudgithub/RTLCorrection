# copy c file to legup direction and make the .v file
thisFileLocation=/home/legup/RTLCorrection/Other/results/dfmul_res2/dfmul_orig
InLegUpPass=/home/legup/legup_original/examples/chstone/dfmul
InLegUpPassCorrection=/home/legup/legup_corrected/examples/chstone/dfmul
InLegUpPassChange=/home/legup/legup_resynthesis/examples/chstone/dfmul
yosysPath=/home/legup/yosys-master
mathingCalcPath=/home/legup/RTLCorrection/Matching/build-matching-Desktop-Debug
Cfilename=softfloat.c
verilogFileName=dfmul.v
cp $thisFileLocation/$Cfilename $InLegUpPass
cd $InLegUpPass
make
cp $verilogFileName $thisFileLocation
cp binding.legup.rpt $thisFileLocation
mv $verilogFileName $yosysPath
# editing .v file and runnig yosys synthesizer to creat main.dot files
cd $yosysPath
awk '{gsub(/\$finish;/,"/*$finish;*/")}1' $verilogFileName > temp.v && mv temp.v $verilogFileName
awk '{gsub(/\@\(negedge clk\);/,"/*@(negedge clk);*/")}1' $verilogFileName > temp.v && mv temp.v $verilogFileName
> syn.ys
echo read_verilog $verilogFileName >> syn.ys
echo write_ilang >> syn.ys
echo hierarchy >> syn.ys
echo proc >> syn.ys
echo opt >> syn.ys
echo show main >> syn.ys
./yosys syn.ys
cd /home/legup
cp -a .yosys_show.dot main.dot
rm .yosys_show.dot
# creating memory_controller.dot file
cd $yosysPath
> syn.ys
echo read_verilog $verilogFileName >> syn.ys
echo write_ilang >> syn.ys
echo hierarchy >> syn.ys
echo proc >> syn.ys
echo opt >> syn.ys
echo show memory_controller >> syn.ys
./yosys syn.ys
cd /home/legup
cp -a .yosys_show.dot memory_controller.dot
rm .yosys_show.dot
# creating c_total.dot
./editfile
rm memory_controller.dot
mv outfile.dot memory_controller.dot
cp main.dot total.dot
cat memory_controller.dot >> total.dot
# cpying c_??.dot files to mathingCalcPath and current directory
cp total.dot main.dot memory_controller.dot $thisFileLocation
cp total.dot main.dot memory_controller.dot $InLegUpPassCorrection
cp total.dot main.dot memory_controller.dot $InLegUpPassChange
mv total.dot main.dot memory_controller.dot $mathingCalcPath

