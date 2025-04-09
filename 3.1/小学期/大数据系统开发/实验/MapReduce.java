//MapReduce.java

//java原生类
import java.io.IOException;//异常处理
import java.util.StringTokenizer;//处理字符串

//Hadoop类
import org.apache.hadoop.conf.Configuration;//Hadoop配置
import org.apache.hadoop.fs.Path;//Hadoop路径
import org.apache.hadoop.hbase.HBaseConfiguration;//HBase配置
import org.apache.hadoop.hbase.client.Put;//写入HBase
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;//HBase用可变字节数组
import org.apache.hadoop.hbase.mapreduce.TableOutputFormat;//HBase输出格式类
import org.apache.hadoop.hbase.util.Bytes;//HBase字节工具，处理字节数组
import org.apache.hadoop.mapreduce.Job;//指向一个MapReduce任务
import org.apache.hadoop.mapreduce.Mapper;//Map父类
import org.apache.hadoop.mapreduce.Reducer;//Reduce父类
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;//MapReduce输入格式类
import org.apache.hadoop.util.GenericOptionsParser;//Hadoop输入参数解析
import org.apache.hadoop.mapreduce.lib.input.FileSplit;//MapReduce输入文件切片类
import org.apache.hadoop.io.Text;//Hadoop文本类


public class MapReduce {
    //map阶段
    public static class Map extends Mapper<Object, Text, Text, Text> {//继承自Mapper类，指明四个泛型参数(KEY_IN,VALUE_IN,KEY_OUT,vALUE_OUT)
        
        private Text keyInfo = new Text();//输出键内容
        private Text valueInfo = new Text();//输出值内容
        private FileSplit split;//输入文件的切片

        public void map(Object key, Text value, Context context) 
        throws IOException, InterruptedException {
            split = (FileSplit) context.getInputSplit();//使用Hadoop提供的FileSplit类获取文件切片
            // 检查 split 是否为 null
            if (split == null) {
                throw new IOException("FileSplit is null. Unable to process the input file.");
            }
            
            StringTokenizer itr = new StringTokenizer(value.toString());
            String fileName = split.getPath().getName();//获取文件名

            while (itr.hasMoreTokens()) {//按行map，采用默认分割符分割即可，键为单词+文件名，值为1

                keyInfo.set(itr.nextToken() + ":" + fileName);
                valueInfo.set("1");
                context.write(keyInfo, valueInfo);
            }
        }
    }

    //combine阶段
    public static class Combine extends Reducer<Text, Text, Text, Text> {//继承自Reducer类，指明四个泛型参数(KEY_IN,VALUE_IN,KEY_OUT,vALUE_OUT)
        private Text info = new Text();//输出值内容

        public void reduce(Text key, Iterable<Text> values, Context context) 
        throws IOException, InterruptedException {
            int sum = 0;//计数器
            


            //开始循环，遍历所有与键关联的值，累加计数器
            for (Text value : values) {
                sum += Integer.parseInt(value.toString());
            }

            //拆分键，将单词与文件名分开，单词为键，文件名：计数器为值，写入上下文
            int splitIndex = key.toString().indexOf(":");//在单词：文件名中定位“：”
            info.set(key.toString().substring(splitIndex + 1) + ":" + sum);//取key.toString()的文件名子串，与sum拼接
            key.set(key.toString().substring(0, splitIndex));//取key.toString()的单词子串，作为键
            context.write(key, info);
        }
    }

    public static class Reduce extends Reducer<Text, Text, ImmutableBytesWritable, Put> {//继承自Reducer类，指明四个泛型参数（KEY_IN,VALUE_IN,KEY_OUT,VALUE_OUT)
        public void reduce(Text key,Iterable<Text>values,Context context)
        throws IOException, InterruptedException {

            //reduce这一步直接将数据写入HBase建好的表格中

            //考虑建立一个文件列表fileList，将所有文件名和计数器进行拼接，以“；”分割
            String fileList = " ";
            
            if(values==null){
                throw new IOException("values is null. Unable to process the input file.");
            }

            for (Text value : values) {
                if(value!=null){
                    fileList += value.toString() + ";";
                }
                else{
                    throw new IOException("value is null. Unable to process the input file.");
                }
            }

            //建立一个Put实例，用于写入HBase
            Put put = new Put(Bytes.toBytes(key.toString()));//写入键值为单词

            put.addColumn(Bytes.toBytes("fileInfo"), Bytes.toBytes("fileList"), Bytes.toBytes(fileList));//写入新的一列，列族为fileInfo,列名为fileList

            context.write(new ImmutableBytesWritable(key.getBytes()), put);//将新的键值对写入上下文
        }
    }
    //主方法
    public static void main(String[] args) 
    throws Exception {
        Configuration conf = HBaseConfiguration.create();//HBaseConfiguration.create() 方法会加载 HBase 和 Hadoop 的相关配置文件，为之后的任务使用

        String[] ioArgs = new String[]{"SplitedData", "output"};//给定默认的输入路径和输出路径。这只是一个初始设置，真正的输入输出路径会从用户输入的命令行参数中解析
        
        //GenericOptionsParser用于解析传递给程序的命令行参数，并将它们应用到配置 conf 中。
        //getRemainingArgs()方法返回未被解析的命令行参数，即输入和输出路径。otherArgs 是一个包含实际传入的输入和输出路径的数组
        String[] otherArgs = new GenericOptionsParser(conf, ioArgs).getRemainingArgs();
        
        //验证是否指定自定义输入和输出目录
        if (otherArgs.length != 2) {
            System.err.println("Usage: Inverted Index <input path> <output path>");
            System.exit(2);
        }


		//创建一个MapReduce的job实例，进行配置并启动
        Job job = new Job(conf, "Inverted Index");//配置文件为conf 名称叫“Inverted Index”
        job.setJarByClass(MapReduce.class);//设置当前类来打包jar文件

        job.setMapperClass(Map.class);//map类
        job.setCombinerClass(Combine.class);//combine类
        job.setReducerClass(Reduce.class);//reduce类

        job.setMapOutputKeyClass(Text.class);//设置map阶段输出键类
        job.setMapOutputValueClass(Text.class);//设置map阶段输出值类
        
        job.setOutputKeyClass(ImmutableBytesWritable.class);//设置reduce后输出键类
        job.setOutputValueClass(Put.class);//设置reduce后输出值类

        //向hbase中写入
        job.setOutputFormatClass(TableOutputFormat.class);//指定输出格式为HBase表格格式，表示输出将写入HBase
        job.getConfiguration().set(TableOutputFormat.OUTPUT_TABLE, "InvertedIndexTable");//指定输出表名为“InvertedIndexTable”

        FileInputFormat.addInputPath(job, new Path(otherArgs[0]));//设置输入路径为用户输入的第一个参数
        
        System.exit(job.waitForCompletion(true) ? 0 : 1);
        
    }
}
