#!/bin/sh

set -e
export LC_ALL=C  # Stable sorting regardless of the locale

. ./build/autogen.d/gen_sources
. ./build/autogen.d/get_ext

no_download=0
if [ "$1" = "-n" ]; then
    no_download=1
fi

slug() {
    echo $(echo $1|tr '/-' '_'|sed 's/^include_measurement_kit/mk/g')
}

gen_headers() {
    rm -f include/measurement_kit/*.hpp
    for name in $(ls include/measurement_kit/); do
        hh=include/measurement_kit/$name.hpp
        echo "// File autogenerated by \`$0\`, do not edit"                > $hh
        echo "#ifndef MEASUREMENT_KIT_$(echo $name|tr 'a-z' 'A-Z')_HPP"   >> $hh
        echo "#define MEASUREMENT_KIT_$(echo $name|tr 'a-z' 'A-Z')_HPP"   >> $hh
        for nn in $(ls include/measurement_kit/$name/); do
            echo "#include <measurement_kit/$name/$nn>"                   >> $hh
        done
        echo "#endif"                                                     >> $hh
    done

    echo "$(slug $1)_includedir = \${prefix}/$1"
    echo "$(slug $1)_include_HEADERS = # Empty"
    for name in `ls $1`; do
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

gen_executables() {
    for name in `ls $2`; do
        if [ ! -d $2/$name ]; then
            if echo $name | grep -q '\.c[p]*$'; then
                bin_name=$(echo $name | sed 's/\.c[p]*$//g')
                echo ""
                echo "if $3"
                echo "    $1 += $2/$bin_name"
                echo "endif"
                echo "$2/$bin_name" >> .gitignore
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

get_geoipdb() {
    echo ""
    base=https://download.maxmind.com/download/geoip/database
    if [ ! -f "test/fixtures/GeoIP.dat" ]; then
        wget -q $base/GeoLiteCountry/GeoIP.dat.gz -O test/fixtures/GeoIP.dat.gz
        gzip -d test/fixtures/GeoIP.dat.gz
    fi
    if [ ! -f "test/fixtures/GeoLiteCity.dat" ]; then
        wget -q $base/GeoLiteCity.dat.gz -O test/fixtures/GeoLiteCity.dat.gz
        gzip -d test/fixtures/GeoLiteCity.dat.gz
    fi
    if [ ! -f "test/fixtures/GeoIPASNum.dat" ]; then
        wget -q $base/asnum/GeoIPASNum.dat.gz -O test/fixtures/GeoIPASNum.dat.gz
        gzip -d test/fixtures/GeoIPASNum.dat.gz
    fi
}

grep -v -E "^(test|example){1}/.*" .gitignore > .gitignore.new
echo test/fixtures/GeoIP.dat >> .gitignore.new
echo test/fixtures/GeoIPASNum.dat >> .gitignore.new
echo test/fixtures/GeoLiteCity.dat >> .gitignore.new
mv .gitignore.new .gitignore

echo "* Generating include.am"
echo "# Autogenerated by $0 on date $(date)"                      > include.am
echo ""                                                          >> include.am
gen_sources libmeasurement_kit_la_SOURCES src/libmeasurement_kit >> include.am
echo ""                                                          >> include.am
gen_headers include/measurement_kit                              >> include.am
gen_executables noinst_PROGRAMS example BUILD_EXAMPLES           >> include.am
gen_executables ALL_TESTS test BUILD_TESTS                       >> include.am

echo "* Updating .gitignore"
sort -u .gitignore > .gitignore.new
mv .gitignore.new .gitignore

if [ $no_download -ne 1 ]; then
    echo "* Fetching dependencies that are built in any case"
    get_ext
    echo "* Fetching geoip database"
    get_geoipdb
fi

echo "* Running 'autoreconf -i'"
autoreconf -i

echo ""
echo "=== autogen.sh complete ==="
echo ""
echo "MeasurementKit is now ready to be compiled. To proceed you shall run"
echo "now the './configure' script that adapts the build to your system."
echo ""
echo "The './configure' script shall also check for external dependencies. "
echo "MeasurementKit external dependencies are:"
echo ""
for depname in `ls build/spec/|grep -v all`; do
    if [ "$depname" != "embedded-mk" ]; then
        echo "    - $depname"
    fi
done
echo ""
echo "If any of these dependencies is missing, the './configure' script shall"
echo "stop and tell you how you could install it."
