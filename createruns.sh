#!/bin/bash

EXECUTABLE=../bm1d_build/BM1D
type=$1
NumberOfSteps=0
NumberOfRuns=0
P0=0
P1=0
x1=0
x2=0
Mu1=0
Mu2=0
Sigma1=0
Sigma2=0
Visible=0
Typeofrun=1
Filename="result.root"


if [ $# -lt 1 ]; then
	echo "u for uniform"
	echo "g for gauss"
	echo "l for layer"
    echo "ua for uniform analyze"
    echo "ga for auss analyze"
    echo "la for layer analyze"
	read -p 'Type: ' type #type get it's value here, or from command line
fi

case $type in

    u)
    if [ $# -ne 7 ]; then #if too few arguments given
        echo "USAGE (Uniform): $0 $1 NumberofSteps NumberofRuns P0 P1 Visible Filename"
		echo "Follow the next steps (Don't leave blank):"
        read -p 'Number of Steps= ' NumberOfSteps
        read -p 'Number of Runs= ' NumberOfRuns
        read -p 'P0= ' P0
        read -p 'P1= ' P1
		read -p 'Visible= ' Visible
		read -p 'ROOT file name+extension(root)= ' Filename
		echo "Next time you can use this: $0 $type $NumberOfSteps $NumberOfRuns $P0 $P1 $Visible $Filename"
    else if [ $# -eq 7 ]; then #set the needed variables
        NumberOfSteps=$2
        NumberOfRuns=$3
        P0=$4
        P1=$5
        Visible=$6
		Filename=$7
	fi
	fi
	$EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible $Typeofrun
    ;;
	
    g)
    if [ $# -ne 8 ]; then #if too few arguments given
        echo "USAGE (Gauss): $0 $1 NumberofSteps NumberofRuns P0 Mu1 Sigma1 Visible Filename"
		echo "Follow the next steps (Don't leave blank):"
        read -p 'Number of Steps= ' NumberOfSteps
        read -p 'Number of Runs= ' NumberOfRuns
		read -p 'P0= ' P0
        read -p 'Mu1= ' Mu1
        read -p 'Sigma1= ' Sigma1
        read -p 'Visible= ' Visible
		read -p 'ROOT file name+extension(root)= ' Filename
		echo "Next time you can use this: $0 $type $NumberOfSteps $NumberOfRuns $P0 $Mu1 $Sigma1 $Visible $Filename"
    else if [ $# -eq 8 ]; then #set the needed variables
		NumberOfSteps=$2
        NumberOfRuns=$3
		P0=$4
		Mu1=$5
		Sigma1=$6
		Visible=$7
		Filename=$8
    fi
	fi
	$EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible $Typeofrun
    ;;
	
    l)
    if [ $# -ne 12 ]; then
        echo "USAGE(Layer): $0 $1 NumberofSteps NumberofRuns P0 x1 x2 Mu1 Mu2 Sigma1 Sigma2 Visible Filename"
		echo "Follow the next steps (Don't leave blank):"
        read -p 'Number of Steps= ' NumberOfSteps
        read -p 'Number of Runs= ' NumberOfRuns
        read -p 'P0= ' P0
        read -p 'x1= ' x1
		read -p 'x2= ' x2
		read -p 'Mu1= ' Mu1
		read -p 'Sigma1= ' Sigma1
		read -p 'Mu2= ' Mu2
		read -p 'Sigma2= ' Sigma2
        read -p 'Visible= ' Visible
		read -p 'ROOT file name+extension(root)= ' Filename
		echo "Next time you can use this: $0 $type $NumberOfSteps $NumberOfRuns $P0 $x1 $x2 $Mu1 $Sigma1 $Mu2 $Sigma2 $Visible $Filename"
    else if [ $# -eq 12 ]; then
         NumberOfSteps=$2
		 NumberofRuns=$3
		 P0=$4
		 x1=$5
		 x2=$6
		 Mu1=$7
		 Mu2=$8
		 Sigma1=$9
		 Sigma2=$10
		 Visible=$11
		 Filename=$12
    fi
	fi
	$EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible $Typeofrun
    ;;

    ua)
    if [ $# -ne 3 ]; then #if too few arguments given
        echo "USAGE (Uniform analyze): $0 $1 Filename"
        echo "Follow the next steps (Don't leave blank):"
        read -p 'ROOT file name+extension(.root)= ' Filename
        read -p 'Visible= ' Visible
        echo "Next time you can use this: $0 $type $Filename $Visible"
        type="u"
        Typeofrun=0
    else if [ $# -eq 3 ]; then #set the needed variables
        Filename=$2
        Visible=$3
        Typeofrun=0
    fi
    fi
    $EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible     $Typeofrun
    ;;

    ga)
    if [ $# -ne 3 ]; then #if too few arguments given
        echo "USAGE (Gauss analyze): $0 $1 Filename"
        echo "Follow the next steps (Don't leave blank):"
        read -p 'ROOT file name+extension(.root)= ' Filename
        read -p 'Visible= ' Visible
        echo "Next time you can use this: $0 $type $Filename $Visible"
        type="g"
        Typeofrun=0
    else if [ $# -eq 3 ]; then #set the needed variables
        Filename=$2
        Visible=$3
        Typeofrun=0
    fi
    fi
    $EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible $Typeofrun
    ;;

    la)
    if [ $# -ne 3 ]; then #if too few arguments given
        echo "USAGE (Layer analyze): $0 $1 Filename"
        echo "Follow the next steps (Don't leave blank):"
        read -p 'ROOT file name+extension(.root)= ' Filename
        read -p 'Visible= ' Visible
        echo "Next time you can use this: $0 $type $Filename $Visible"
        type="l"
        Typeofrun=0
    else if [ $# -eq 3 ]; then #set the needed variables
        Filename=$2
        Visible=$3
        Typeofrun=0
        fi
        fi
    $EXECUTABLE $NumberOfSteps $NumberOfRuns $P0 $P1 $x1 $x2 $Mu1 $Mu2 $Sigma1 $Sigma2 $Filename $type $Visible $Typeofrun
;;

	help)
		echo "USAGE:"
		echo "Simply call $0 and follow the next steps,"
		echo "or you can give the arguments directly from command line:"
		echo "Uniform: $0 u NumberofSteps NumberofRuns P0 P1"
		echo "Gaus: $0 g NumberofSteps NumberofRuns Mu1 Sigma1"
		echo "Layer: $0 $1 NumberofSteps NumberofRuns P0 x1 x2 Mu1 Mu2 Sigma1 Sigma2 Visible Filename"
	;;
		
    *)
		echo "USAGE:"
		echo "Simply call $0 and follow the next steps,"
		echo "or you can give the arguments directly from command line:"
		echo "Uniform: $0 u NumberofSteps NumberofRuns P0 P1"
		echo "Gaus: $0 g NumberofSteps NumberofRuns Mu1 Sigma1"
		echo "Layer: $0 $1 NumberofSteps NumberofRuns P0 x1 x2 Mu1 Mu2 Sigma1 Sigma2 Visible Filename"
esac
