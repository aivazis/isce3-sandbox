      subroutine doppler_setSamples(varInt)
       use dopplerState
       implicit none
       integer varInt
       i_samples = varInt
      end

      subroutine doppler_setStartLine(varInt)
       use dopplerState
       implicit none
       integer varInt
       i_strtline = varInt
      end

      subroutine doppler_setLines(varInt)
       use dopplerState
       implicit none
       integer varInt
       i_nlines = varInt
      end
