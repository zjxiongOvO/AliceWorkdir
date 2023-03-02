filename="LHC22p_pass3_subset"
dataname="LHC22p_pass3_subset"

cutname1="BeforeCuts"
cutname2="Jpsi_TPCPost_calib_debug4"
# cutname3="Jpsi_TPCPost_calib_noITSCuts_debug4"
# root -l -q -b code/qa4run3.cxx'("'$filename'","'$dataname'","'$cutname1'")'
# root -l -q -b code/qa4run3.cxx'("'$filename'","'$dataname'","'$cutname2'")'
# root -l -q -b code/qa4itstpc.cxx'("'$filename'","'$dataname'","'$cutname1'")'
root -l -q -b code/qa4itstpc.cxx'("'$filename'","'$dataname'","'$cutname2'")'
# root -l -q -b code/qa4pair.cxx'("'$filename'","'$dataname'","'$cutname2'")'
# root -l signalextractioncheck.cxx'("'$filename'","'$dataname'")'
# root -l -q -b code/qa4vtx.cxx'("'$filename'","'$dataname'")'

# filename1="LHC22r_pass2_subset_lowIR"
# filename2="LHC22r_pass2_subset"
# dataname="LHC22r_pass2"

# root -l -b -q qa4compare.cxx'("'$filename1'","'$filename2'","'$dataname'")'