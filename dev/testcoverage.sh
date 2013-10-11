#!/bin/bash
cd ../build

echo "Clear Coverage Data"
lcov --zerocounters --directory ../ -output-file coverage.info

echo "Executing Test Suite"
out/unit_testsuite
echo "Executing stubgenerator"
out/jsonrpcstub -i ../src/example/spec.json --cpp=stubclient.h --server=stubserver.h -c Stub

echo "Executing Stubs"
out/stubserver &
out/stubclient

killall stubserver

echo "Grabbing Coverage"
lcov --capture --directory ../ --output-file coverage.info
lcov --remove coverage.info "/usr/*" -o coverage.info
lcov --remove coverage.info "*mongoose.c" -o coverage.info

echo "Generate HTML report"
genhtml coverage.info --output-directory coverage
xdg-open coverage/index.html
cd ../dev

