# copy c file to legup direction and make the .v file
thisFileLocation=/home/legup/RTLCorrection/Other/results/motion_res2/motion_corrected
InLegUpPass=/home/legup/legup_corrected/examples/chstone/motion
yosysPath=/home/legup/yosys-master
mathingCalcPath=/home/legup/RTLCorrection/Matching/build-matching-Desktop-Debug
Cfilename=motion.c
verilogFileName=mpeg2.v
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
mv main.dot c_main.dot
mv memory_controller.dot c_memory_controller.dot
mv total.dot c_total.dot
# cpying c_??.dot files to mathingCalcPath and current directory
cp c_total.dot $thisFileLocation
cp c_main.dot $thisFileLocation
cp c_memory_controller.dot $thisFileLocation
mv c_total.dot $mathingCalcPath
mv c_main.dot $mathingCalcPath
mv c_memory_controller.dot $mathingCalcPath
cd $mathingCalcPath
./matching 
mv result.txt $thisFileLocation

