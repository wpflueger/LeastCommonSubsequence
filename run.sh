#!/bin/bash
# LEN=20000

# export OMP_NUM_THREADS=1
# LENS = 10 100 1000 5000 7500 10000 20000 30000 40000 50000 

for LEN in 10 100 1000 5000 7500 10000 20000 30000 40000 50000 
do 
echo "+++++++++++++++" &>> out.txt
    echo "Length: $LEN" &>>  out.txt
    ./sequence $LEN $LEN
    for j in {0..4}
    do
    echo "===============" &>>  out.txt
    echo "Try: $j" &>>  out.txt
        for i in {1..1}
        do 
            echo "Thread: $i" &>>  out.txt
            export OMP_NUM_THREADS=$i
            sudo perf stat ./lcs text1.dat text2.dat $LEN $LEN $i &>> out.txt
        done
    done
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