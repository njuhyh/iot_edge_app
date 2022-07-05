function log(){
    echo `date "+%Y-%m-%d %T"`: $1
}

log "[INFO] start execute process."

# 这里的路径取决于项目保存的位置
cd /opt/iot/edge/MyCApp

./MyCApp
