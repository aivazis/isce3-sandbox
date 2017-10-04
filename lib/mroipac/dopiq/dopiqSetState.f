        subroutine dopiq_setLineLength(varInt)
        use dopiqState
        implicit none
        integer varInt
        len = varInt
        end

        subroutine dopiq_setLineHeaderLength(varInt)
        use dopiqState
        implicit none
        integer varInt
        hdr = varInt
        end

        subroutine dopiq_setLastSample(varInt)
        use dopiqState
        implicit none
        integer varInt
        last = varInt
        end

        subroutine dopiq_setStartLine(varInt)
        use dopiqState
        implicit none
        integer varInt
        i0 = varInt
        end

        subroutine dopiq_setNumberOfLines(varInt)
        use dopiqState
        implicit none
        integer varInt
        n = varInt
        end

        subroutine dopiq_setMean(varDbl)
        use dopiqState
        implicit none
        real*8 varDbl
        xmn = varDbl
        end

        subroutine dopiq_setPRF(varDbl)
        use dopiqState
        implicit none
        real*8 varDbl
        prf = varDbl
        end
