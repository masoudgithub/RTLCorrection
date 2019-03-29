#copy the editfile to home directory, create main.dot and memory_controller.dot using yosys and then 
# run this bash script to creat edit memory_controller.dot and creat total.dot
./editfile
rm memory_controller.dot; mv outfile.dot memory_controller.dot
echo memory_controller.dot is eddited.
cp main.dot total.dot
cat memory_controller.dot >> total.dot
echo total file is created.

