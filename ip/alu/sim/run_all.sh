#! /bin/bash
#
# This convenience will build and run all simulations in this
# direcory.

CONTINUE=0 # continue on failures

while [[ $# -gt 0 ]]; do
  case $1 in
    -c|--continue)
      CONTINUE=1
      shift
      ;;
    -*|--*)
      echo "Unknown option $1"
      exit 1
      ;;
  esac
done

# A running list of failed simulations to print at the end of
# the script. This is mostly useful when the CONTINUE flag is
# set.
#
FAILURES=""

# This list contains the subdirectories that have the simulation
# Makefiles. The Makefiles must have a "run" target.
#
SIMS=""
SIMS="${SIMS} and_block"
SIMS="${SIMS} not_block"
SIMS="${SIMS} or_block"
SIMS="${SIMS} xor_block"
SIMS="${SIMS} alu"

# Build and attempt to run each simulation.
#
for sim in ${SIMS}
do
    make -C "$sim"

    make -C "$sim" run || {
        echo "Simulation \"$sim\" failed."
        FAILURES="${FAILURES} $sim"

        if [ $CONTINUE -eq 0 ]; then
            exit 1
        fi
    }
done

# Display the final results of running all the simulations
#
if [ -z "$FAILURES" ]; then
    echo ""
    echo "All simulations passed!"
    exit 0
else
    echo ""
    echo "The following simulations failed:"
    for f in $FAILURES
    do
        echo "    $f"
    done

    exit 1
fi
