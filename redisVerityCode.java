//install package Jedis
import redis.clients.jedis.Jedis;

import java.util.Random;

public class redisVerityCode {
    private static String verCode;
    public static void main(String[] args) {
        //模拟验证码发送
        SendCode("137000000");
        try {
            Thread.sleep(300000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        //校验发送的验证码
        var res=VerityCode("137000000",verCode);
        if(res){
            System.out.println("验证成功");
        }else{
            System.out.println("验证失败");
        }
    }

    //1.随即生成一个六位数的验证码
    public static String generateCode(){
        Random random = new Random();
        StringBuilder str= new StringBuilder();
        for(int i=0;i<6;++i){
            str.append(random.nextInt(9));
        }
        verCode = str.toString();
        return str.toString();
    }
    public static void SendCode(String phoneNumber){
        String verityCountKey = "Verity:"+phoneNumber+":count";
        String verityCodeKey = "Verity:"+phoneNumber+":Code";
        Jedis jedis = new Jedis("xxxxip",6379);
        jedis.auth("password");
        String val = jedis.get(verityCountKey);
        if(val == null){
            jedis.setex(verityCountKey,60*60*24,"1");
        }else if (Integer.parseInt(val)<=2){
            jedis.incr(verityCountKey);
        }else{
            System.out.println("今天发送的次数已经达到3次了，不能再发送了");
        }

        jedis.setex(verityCodeKey,60*2,generateCode());
        jedis.close();
    }

    public static boolean VerityCode(String phoneNumber,String Code){
        Jedis jedis = new Jedis("xxxxip",6379);
        jedis.auth("password");
        String verityCodeKey = "Verity:"+phoneNumber+":Code";
        String val = jedis.get(verityCodeKey);
        jedis.close();
        if (val==null|| !val.equals(Code)){
            return false;
        }else{
            return true;
        }

    }


}
