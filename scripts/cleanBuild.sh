if [ -d "../build" ]; then
    rm -rf ../build
else
    echo "nothing to clean, build file doesnt exists."
fi