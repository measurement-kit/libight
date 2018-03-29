#!/bin/sh

set -e
export LC_ALL=C  # Stable sorting regardless of the locale

. build/autogen.d/geoip

no_geoip=0
cmake=0
while [ $# -gt 0 ]; do
    opt=$1; shift
    if [ "$opt" = "--no-geoip" -o "$opt" = "-n" ]; then
        no_geoip=1
    elif [ "$opt" = "--cmake" ]; then
        cmake=1
    else
        echo "usage: $0 [--cmake] [-n|--no-geoip]" 1>&2
        exit 1
    fi
done

slug() {
    echo $(echo $1|tr '/-' '_'|sed 's/^include_measurement_kit/mk/g')
}

gen_headers() {
    echo "$(slug $1)_includedir = \${prefix}/$1"
    echo "$(slug $1)_include_HEADERS = # Empty"
    for name in `ls $1|grep -v '\.in$'`; do
        if [ ! -d $1/$name ]; then
            echo "$(slug $1)_include_HEADERS += $1/$name"
        fi
    done
    echo ""
    for name in `ls $1`; do
        if [ -d $1/$name ]; then
            gen_headers $1/$name
        fi
    done
}

gen_sources() {
    for name in `ls $2`; do
        if [ ! -d $2/$name ]; then
            if echo $name | grep -q '\.c[p]*$'; then
                echo "$1 += $2/$name"
            fi
        fi
    done
    for name in `ls $2`; do
        if [ -d $2/$name ]; then
            gen_sources $1 $2/$name
        fi
    done
}

gen_executables() {
    for name in `ls $2`; do
        if [ ! -d $2/$name ]; then
            if echo $name | grep -q '\.c[p]*$'; then
                bin_name=$(echo $name | sed 's/\.c[p]*$//g')
                echo ""
                echo "if $3"
                echo "    $1 += $2/$bin_name"
                echo "endif"
                echo "$(slug $2/$bin_name)_SOURCES = $2/$name"
                echo "$(slug $2/$bin_name)_LDADD = libmeasurement_kit.la"
            fi
        fi
    done
    for name in `ls $2`; do
        if [ -d $2/$name ]; then
            gen_executables $1 $2/$name $3
        fi
    done
}

if [ $cmake -eq 0 ]; then
    echo "* Generating include.am"
    echo "# Autogenerated by $0 on date $(date)"                      > include.am
    echo ""                                                          >> include.am
    gen_sources libmeasurement_kit_la_SOURCES src/libmeasurement_kit >> include.am
    gen_sources measurement_kit_SOURCES src/measurement_kit          >> include.am
    echo ""                                                          >> include.am
    gen_headers include/measurement_kit                              >> include.am
    gen_executables noinst_PROGRAMS example BUILD_EXAMPLES           >> include.am
    gen_executables ALL_TESTS test BUILD_TESTS                       >> include.am
else
    echo "* Updating cmake/AutoGenerated.cmake"
    echo "# Autogenerated by $0 on date $(date)"               > cmake/AutoGenerated.cmake
    echo ""                                                   >> cmake/AutoGenerated.cmake
    for SRC in `find example -type f -name \*.cpp|sort`; do
        BASENAME=`basename $SRC | sed 's/\.cpp$//g'`
        DIRNAME=`dirname $SRC`
        echo "mk_declare_example(\"$DIRNAME\" \"$BASENAME\")" >> cmake/AutoGenerated.cmake
    done
    echo ""                                                   >> cmake/AutoGenerated.cmake
    for SRC in `find test -type f -name \*.cpp|sort`; do
        BASENAME=`basename $SRC | sed 's/\.cpp$//g'`
        DIRNAME=`dirname $SRC`
        echo "mk_declare_test(\"$DIRNAME\" \"$BASENAME\")"    >> cmake/AutoGenerated.cmake
    done
fi

if [ $no_geoip -ne 1 ]; then
    autogen_get_geoip
fi

if [ $cmake -eq 0 ]; then
    echo "* Running 'autoreconf -i'"
    autoreconf -i
else
    echo "* Generating './cmake/make.cmake'"
    ./script/cmake/autogen > ./cmake/make.cmake
fi

echo ""
echo "=== autogen.sh complete ==="
echo ""

if [ $cmake -eq 0 ]; then
    echo "MeasurementKit is now ready to be compiled. To proceed you shall run"
    echo "now the './configure' script that adapts the build to your system."
    echo ""
    echo "The './configure' script shall also check for external dependencies. "
    echo "MeasurementKit external dependencies are:"
    echo ""
    echo "    - GeoIP"
    echo "    - openssl / libressl"
    echo "    - libevent"
    echo ""
    echo "If any of these dependencies is missing, the './configure' script"
    echo "shall stop and tell you how you could install it."
else
    echo "MeasurementKit is now ready to be compiled. To proceed you shall run"
    echo "either 'cmake' directly or our friendly './script/cmake/run' wrapper"
    echo "script. The latter attempts to apply smart settings in case you are"
    echo "running 'cmake' on macOS and have brew installed."
fi

echo ""
