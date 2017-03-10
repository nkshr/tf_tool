#!/bin/sh

fname=$1

if [ $# -ne 2 ]; then
    echo "Error : Invalid number of arguments"
    echo "./gather_images.sh <list of images> <directory images is copied to>"
    exit 1
fi

if [ ! -e $1 ]; then
    echo "Error : list of images &1 does not exist."
    exit 1
fi
fname=$1

if [ ! -d $2 ]; then
    echo "Error : Directory $2 does not exist."
    exit 1
fi
dname=$2

num_imgs=0
for line in `cat $fname`
do
    if [ ! -e $1 ]; then
	echo "$1 does not exist."
	exit 1
    fi

    num_imgs=`expr $num_imgs + 1`
    tmp=`expr $num_imgs % 1000`
    if [ $tmp -eq 0 ]; then
	echo "$num_imgs images were detected."
    fi
done

echo "number of images is $num_imgs."
cnt=0
for line in `cat $fname`
do
    cnt=`expr $cnt + 1`
    img_name=`basename "$line"`
    img_copied=$dname/$img_name
    echo "$line is copied to dname $img_copied ($cnt / $num_imgs)." 
done

