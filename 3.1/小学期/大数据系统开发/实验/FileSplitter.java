//FileSplitter.java
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;

public class FileSplitter {
    public static void main(String[] args) {
        // 源文件路径
        String sourceFilePath = "sentences.txt";

        // 目标文件路径前缀
        File dataDirectory = new File("/root/SplitedData");//指定目标文件夹
        if(!dataDirectory.exists()){
            dataDirectory.mkdir();
        }
        String targetFilePrefix = "/root/SplitedData/split_";

        // 每个文件的最大行数
        int maxLinesPerFile = 10000;

        //为当前filereader给定buffer
        try{
            BufferedReader reader = new BufferedReader(new FileReader(sourceFilePath));

            //行缓存
            String line;

            //计数器
            int lineCount = 0;
            int fileCount = 0;

            BufferedWriter writer = new BufferedWriter(new FileWriter(targetFilePrefix + fileCount + ".txt"));

            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine();
                lineCount++;

                if (lineCount >= maxLinesPerFile) {
                    writer.close();
                    lineCount = 0;
                    fileCount++;
                    writer = new BufferedWriter(new FileWriter(targetFilePrefix + fileCount + ".txt"));
                }
            }
            writer.close();
            reader.close();
        }catch(IOException e){
            e.printStackTrace();
        }
        System.out.println("文件分割完成");
    }
}
