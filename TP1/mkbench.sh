#!/bin/bash

# Date variable
echo "Loading gcc 7.2.0"
module load gcc/7.2.0

echo "Creating folders"

mkdir -p benchmarks
mkdir -p benchmarks/results/
mkdir -p benchmarks/bin

echo "Done"

echo "Compiling benchmarks"

# Euclidean Distance = sqrt( (x1-x2)^2 + (y1-y2)^2 )
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=1 -DCLUSTER_FUNC=1" BNC_SUFFIX="_sqrt" BNC_EXEC="kmeans"

# Euclidean Distance = (x1-x2)^2 + (y1-y2)^2
# Make all targets w/o optimizations
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=2" BNC_SUFFIX="_u2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=3" BNC_SUFFIX="_u4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=4" BNC_SUFFIX="_u8" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=5" BNC_SUFFIX="_b" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=6" BNC_SUFFIX="_bu2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=7" BNC_SUFFIX="_bu4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=8" BNC_SUFFIX="_bu8" BNC_EXEC="kmeans"

# Make all targets w/ -O3
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="_o3" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=2" BNC_SUFFIX="_o3_u2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=3" BNC_SUFFIX="_o3_u4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=4" BNC_SUFFIX="_o3_u8" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=5" BNC_SUFFIX="_o3_b" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=6" BNC_SUFFIX="_o3_bu2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=7" BNC_SUFFIX="_o3_bu4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=8" BNC_SUFFIX="_o3_bu8" BNC_EXEC="kmeans"

# Make all targets w/ -O3 -ftree-loop-if-convert
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="_o3_tlic" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=2" BNC_SUFFIX="_o3_tlic_u2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=3" BNC_SUFFIX="_o3_tlic_u4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=4" BNC_SUFFIX="_o3_tlic_u8" BNC_EXEC="kmeans"

# Make all targets w/ -O3 -ffast-math -ftree-loop-if-convert
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="_o3_tlic_ffm" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=2" BNC_SUFFIX="_o3_tlic_ffm_u2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=3" BNC_SUFFIX="_o3_tlic_ffm_u4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=4" BNC_SUFFIX="_o3_tlic_ffm_u8" BNC_EXEC="kmeans"

# Make all targets w/ -O3 -ffast-math -ftree-loop-if-convert -flto
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -flto -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="_o3_tlic_ffm_lto" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -flto -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=2" BNC_SUFFIX="_o3_tlic_ffm_lto_u2" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -flto -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=3" BNC_SUFFIX="_o3_tlic_ffm_lto_u4" BNC_EXEC="kmeans"
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -flto -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=4" BNC_SUFFIX="_o3_tlic_ffm_lto_u8" BNC_EXEC="kmeans"

# Make all targets w/ -O3 -ffast-math -ftree-loop-if-convert -flto -fwhole-program omp simd
make benchmark BNC_CFLAGS="-Wall -Wextra -Werror -lm -fopt-info -O3 -ftree-loop-if-convert -ffast-math -flto -fopenmp -DEUCLIDEAN_FUNC=2 -DCLUSTER_FUNC=1" BNC_SUFFIX="_o3_tlic_ffm_lto_omp" BNC_EXEC="kmeans"

echo "Done"