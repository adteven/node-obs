SLOBS_DIR='../slobs-client/'
BUILD_DIR='build'

cmake-js configure --runtime electron --runtime-version 1.7.7 --CDNODE_OBS_DIST="../../slobs-client"
cmake-js compile --runtime electron --runtime-version 1.7.7

rm -rf "${SLOBS_DIR}/node-obs"
cp -rf "${BUILD_DIR}/distribute/node-obs" "${SLOBS_DIR}/node-obs"