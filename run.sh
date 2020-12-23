#!/bin/bash
# LEN=20000

# export OMP_NUM_THREADS=1
# LENS = 10 100 1000 5000 7500 10000 20000 30000 40000 50000 

for LEN in  70000 80000 90000
do 
echo "+++++++++++++++" &>> large_out.txt
    echo "Length: $LEN" &>>  large_out.txt
    ./sequence $LEN $LEN
    # for j in {0..4}
    # do
    # echo "===============" &>>  large_out.txt
    # echo "Try: $j" &>>  large_out.txt
        for i in {3..6}
        do 
            echo "Thread: $i" &>>  large_out.txt
            export OMP_NUM_THREADS=$i
            sudo perf stat ./lcs text1.dat text2.dat $LEN $LEN $i &>> large_out.txt
        done
    # done
done



# #!/bin/bash
# LEN=10000
# ./sequence $LEN $LEN
# # export OMP_NUM_THREADS=1

# for i in {1..6}
# do 
#     echo $i
#     # export OMP_NUM_THREADS=$i
#     sudo perf stat ./lcs_pthreads string1.txt string2.txt $i
# done
# echo openmp
# for i in {1..6}
# do 
#     echo $i
#     # export OMP_NUM_THREADS=$i
#     sudo perf stat ./lcs_openmp string1.txt string2.txt $i
# done
