# copy c file to legup direction and make the .v file
InLegUpPass=/home/legup/original_legup/examples/chstone/sha
yosysPath=/home/legup/yosys-master
mathingCalcPath=/home/legup/RTLCorrection/Matching/build-matching-Desktop-Debug
Cfilename=sha.c
verilogFileName=sha_driver.v
cp $PWD/$Cfilename $InLegUpPass
cd $InLegUpPass
make
cp $verilogFileName $PWD
mv $verilogFileName $yosysPath
# editing .v file and runnig yosys synthesizer to creat main.dot files
cd /home/legup/yosys-master
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
cd /home/legup/yosys-master
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
rm memory_controller.dot; mv outfile.dot memory_controller.dot
echo memory_controller.dot is eddited.
cp main.dot total.dot
cat memory_controller.dot >> total.dot
echo total file is created.
mv main.dot c_main.dot
mv memory_controller.dot c_memory_controller.dot
mv total.dot c_total.dot
# cpying c_??.dot files to mathingCalcPath and current directory
cp c_total.dot $PWD
cp c_main.dot $PWD
cp C_memory_controller.dot $PWD

mv c_total.dot $mathingCalcPath
mv c_main.dot $mathingCalcPath
mv C_memory_controller.dot $mathingCalcPath
cd $mathingCalcPath
./matching 
mv result.txt $PWD
