clear
echo Creating Environment for Compiling Kernel...
chmod --recursive 777 *
export USE_CCACHE=1
clear
echo Environment sucessfully created

#!/bin/sh
# Custom build script


KERNEL_DIR=$PWD
ZIMAGE=$KERNEL_DIR/outdir/arch/arm64/boot/Image.gz-dtb
BUILD_START=$(date +"%s")
blue='\033[0;34m'
cyan='\033[0;36m'
yellow='\033[0;33m'
red='\033[0;31m'
nocol='\033[0m'

#make kernel compiling dir...
mkdir -p outdir


#exports ::
#toolchain , custom build_user , custom build_host , arch
export ARCH=arm64
export ARCH_MTK_PLATFORM=mt6735
export CROSS_COMPILE=$PWD/tools/toolchain/bin/aarch64-linux-android-
export KBUILD_BUILD_USER="DennisMurimi™"
export KBUILD_BUILD_HOST="AndroidHQ254Projects"


compile_kernel ()
{
echo -e "$blue***********************************************"
echo "          Compiling Kernel...          "
echo -e "***********************************************$nocol"
echo ""
#hot4pro defconfig
make -C $PWD O=outdir ARCH=arm64 rlk6737m_open_n_defconfig
#
make -j24 -C $PWD O=outdir ARCH=arm64
echo -e "$yellow Copying to outdir/custom_kernel $nocol"
cp outdir/arch/arm64/boot/Image.gz-dtb outdir/custom_kernel/Image

if ! [ -f $ZIMAGE ];
then
echo -e "$red Kernel Compilation failed! Fix the errors! $nocol"
exit 1
fi
}

zip_zak ()
{
echo -e "$cyan***********************************************"
echo "          ZIpping Kernel...          "
echo -e "***********************************************$nocol"
echo ""
echo -e "$yellow Putting custom_kernel™ Kernel in Recovery Flashable Zip $nocol"
#using lazy kernel flasher
cd outdir
cd custom_kernel
    if 
    [ -f outdir/custom_kernel/out_done ] 
    then
    rm -rf out_done
    else
    make
    mkdir -p out_done
    cp Hot4pro.Oreo*zip* out_done
    cd ../../
    sleep 0.6;
    echo ""
    echo ""
    echo "" "Done Making Recovery Flashable Zip"
    echo ""
    echo ""
    echo "" "Locate custom_kernel™ Kernel in the following path : "
    echo "" "outdir/custom_kernel/out_done"
    echo ""
    echo -e "$blue***********************************************"
    echo "          Uploading Kernel as zip...          "
    echo -e "***********************************************$nocol"
    echo ""
    curl --upload-file outdir/custom_kernel/out_done/Hot4pro.Oreo*.zip https://transfer.sh/Hot4pro.Oreo_8.x_$BUILD_START.zip
    echo ""
    echo ""
    echo " Uploading Done !!!"
    echo ""
    echo ""
    BUILD_END=$(date +"%s")
    DIFF=$(($BUILD_END - $BUILD_START))
    echo -e "$yellow Build completed in $(($DIFF / 60)) minute(s) and $(($DIFF % 60)) seconds.$n"
    exit 1
    fi
}
case $1 in
clean)
#make ARCH=arm64 -j16 clean mrproper
rm -rf include/linux/autoconf.h
;;
*)
compile_kernel
zip_zak
;;
esac
