%JAVA17_HOME%\bin\java -Djasypt.encryptor.password=yourSecretKey -jar target\AutoLoginProject-1.0-SNAPSHOT.jar
java -cp jasypt-1.9.3.jar org.jasypt.intf.cli.JasyptPBEStringEncryptionCLI input="YourPassword" password="SecretKey" algorithm=PBEWithMD5AndDES
./encrypt.sh password=MYPAS_WORD verbose=false input="This is my message to be encrypted"
./decrypt.sh password=MYPAS_WORD verbose=false input="k1AwOd5XuW4VfPQtEXEdVlMnaNn19hivMbn1G4JQgq/jArjtKqryXksYX4Hl6A0e"

mvn spring-boot:run -Djasypt.encryptor.password="Pakistan is my country" OR export JASYPT_ENCRYPTOR_PASSWORD="Pakistan is my country"
export ENV_PASSPHRASE="Pakistan is my country"
set ENV_PASSPHRASE="Pakistan is my country"
/t/ThirdParty/Java/jasypt-1.9.3/bin/encrypt.sh password="${ENV_PASSPHRASE}" verbose=false input="Choh@n47"
/t/ThirdParty/Java/jasypt-1.9.3/bin/decrypt.sh password="${ENV_PASSPHRASE}" verbose=false input="qI3KryxlnrOq33S0bXGWCqwC6Trr6ywp"
