# copy c file to legup direction and make the .v file
thisFileLocation=/home/legup/RTLCorrection/Other/results/fft_res1/fft_changed
InLegUpPass=/home/legup/legup_changed/examples/fft
yosysPath=/home/legup/yosys-master
mathingCalcPath=/home/legup/RTLCorrection/Matching/build-matching-Desktop-Debug
Cfilename=fft.c
verilogFileName=fft.v
cp $thisFileLocation/$Cfilename $InLegUpPass
cd $InLegUpPass
make
cp $verilogFileName $thisFileLocation
mv $verilogFileName $yosysPath
# editing .v file and runnig yosys synthesizer to creat main.dot files
cd $yosysPath
source run.sh $verilogFileName
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
rm c_total.dot
rm c_main.dot
rm c_memory_controller.dot

