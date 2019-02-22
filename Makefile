OS = $(shell uname)
ifeq ($(OS), Darwin) # if developing on MacOS machine
	CXX = g++
	AR = libtool -static -o 
else # defaults to the C++ compiler from a devtoolset-7
	CXX = /opt/rh/devtoolset-7/root/usr/bin/g++
	AR = ar rcs
endif
CXXFLAGS = -std=c++11
INCLUDES =
Main = UBXPf0113_0853
Objs = $(Main).o
Lib = lib$(Main).a

all: $(Main)
.PHONY: all clean

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(Lib): $(Objs)
	$(AR) $@ $(Objs)

$(Main): $(Main)-main.o $(Lib)
	$(CXX) $(CXXFLAGS) -o $@ $(Main)-main.o -L. -l$(Main)

clean:
	rm -f *.o $(Main) $(Lib)

## data pre-processing
# generate the C++ data points from cohort query result
acurve: acurve-all.txt
	echo "const vector<vector<double>> aCurve"; echo '{'; \
	for term in 30 15; do for agency in fn fh g2 g1; do \
		prod=$$(echo $$agency |tr '[a-z]' '[A-Z]')$$term; \
		echo "{ // $$prod"; \
		awk -F"\t" -v term=$$term '/^'$${agency}_fix_$${term}'/ && $$2<=term*12{ \
                    print ($$2==0 && $$3!~/[0-9]/? 0: $$3)}' acurve-all.txt | \
			fmt -w 100 |grep -Ev '^$$' |sed 's/ /,/g; s/$$/,/'; echo '},'; \
	done; done; echo '};'

scurve: scurve-all.txt
	for term in 30 15; do for agency in fn fh g2 g1; do \
		prod=$$(echo $$agency |tr '[a-z]' '[A-Z]')$$term; \
		if [ $$prod = FN30 ]; then echo "const vector<vector<pair<int, double>>> sCurves"; echo '{'; fi; \
		echo { // $$prod; \
		grep ^$${agency}_fix_$${term} scurve-all.txt |cut -f2,3 |sed 's/  *//g; s/^/{/; s/	/,/; s/$$/},/;' | \
		fmt -w 100; echo },; \
	done; done;  echo '};'; 

season: season-all.txt
	for term in 30 15; do for agency in fn fh g2 g1; do \
		prod=$$(echo $$agency |tr '[a-z]' '[A-Z]')$$term; \
		if [ "$$prod" = FN30 ]; then \
			echo 'const vector<vector<double>> Seasonality'; \
			grep fn_fix_30 season-all.txt |cut -f3 |tr '\n' ' ' |sed 's/ /     /g; s/^ */{ \/\/ /;'; \
		fi; \
		echo '{'$$(grep $${agency}_fix_$${term} season-all.txt |cut -f4 | \
			tr -d ' ' |tr '\n' ',' |sed 's/^,//; s/,$$//' )"}, // $$prod"; \
	done; done; echo '};'

