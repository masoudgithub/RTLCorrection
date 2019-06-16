# copy c file to legup direction and make the .v file
thisFileLocation=/home/legup/RTLCorrection/Other/results/sha_res_2/sha_orig
InLegUpPass=/home/legup/legup_original/examples/chstone/sha
InLegUpPassCorrection=/home/legup/legup/examples/chstone/sha
InLegUpPassChange=/home/legup/legup_changed/examples/chstone/sha
yosysPath=/home/legup/yosys-master
mathingCalcPath=/home/legup/RTLCorrection/Matching/build-matching-Desktop-Debug
Cfilename=sha.c
verilogFileName=sha_driver.v
cp $thisFileLocation/$Cfilename $InLegUpPass
cd $InLegUpPass
make
cp $verilogFileName $thisFileLocation
mv $verilogFileName $yosysPath
# editing .v file and runnig yosys synthesizer to creat main.dot files
cd $yosysPath
source run.sh sha_driver.v
> syn.ys
echo read_verilog sha_driver.v >> syn.ys
echo write_ilang >> syn.ys
echo hierarchy >> syn.ys
echo proc >> syn.ys
echo opt >> syn.ys
echo show main >> syn.ys
./yosys syn.ys
cd /home/legup
cp -a .yosys_show.dot main.dot
rm -a .yosys_show.dot
# creating memory_controller.dot file
cd $yosysPath
> syn.ys
echo read_verilog sha_driver.v >> syn.ys
echo write_ilang >> syn.ys
echo hierarchy >> syn.ys
echo proc >> syn.ys
echo opt >> syn.ys
echo show memory_controller >> syn.ys
./yosys syn.ys
cd /home/legup
cp -a .yosys_show.dot memory_controller.dot
rm -a .yosys_show.dot
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

