USE_HIP = TRUE

ifeq ($(USE_HIP),TRUE)
  CXX = hipcc
  CXXFLAGS = -std=c++17 -m64 -g -O3 -Wno-unused-result --amdgpu-target=gfx906,gfx908 -fgpu-rdc
  LINKFLAGS = --amdgpu-target=gfx906,gfx908 -fgpu-rdc
else
  nvcc_version := $(shell nvcc --version | grep "release" | awk 'BEGIN {FS = ","} {print $$2}' | awk '{print $$2}')
  nvcc_major_lt_11 = $(shell expr $(nvcc_major_version) \< 11)
  ifeq ($(nvcc_major_lt_11),1)
    $(error nvcc 11 is required for CUDA build)
  endif

  CXX = nvcc
  CXXFLAGS = -ccbin=g++ -Xcompiler='-g -O3 -std=c++17' --std=c++17 -m64 -arch=compute_70 -code=sm_70 --expt-extended-lambda -dc -x cu
  LINKFLAGS = -arch=compute_70 -code=sm_70
endif

test.ex: main.o init.o work.o
	$(CXX) $(LINKFLAGS) -o $@ $^

init.o: init.cpp init.H par.H
	$(CXX) $(CXXFLAGS) -c -o $@ $<

work.o: work.cpp work.H par.H
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	${RM} *.o *.ex

FORCE:

.PHONY: clean
