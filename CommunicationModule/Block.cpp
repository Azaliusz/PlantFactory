#include "Block.h"

Block::Block(String block_name)
{

  Block_Name = block_name;
  Block_ID=100;
  Enable=true;
  //TEST
  AddModul(1, 1);
  AddModul(2, 1);
  AddModul(3, 1);
  AddModul(4, 1);
  AddModul(5, 1);
  AddModul(6, 1);
  AddModul(7, 1);
  
}

void Block::RefressALL()
{
  for (int i = 0; i < SensorModules.size(); ++i)
  {
    if (SensorModules.get(i)->Is_Enabled)
    {
      SensorModules.get(i)->RefressValues();
    }
  }
}

String Block::ShowBlock()
{
  String ret="";
  ret+=">>Name: "+Block_Name+" ("+Block_ID+"):"+Enable+"\n";
  
  ret+=">>  SensorModules:\n";
  for (int i = 0; i < SensorModules.size(); ++i)
  {
   ret+=SensorModules.get(i)->ShowModul()+"\n";
  }

  ret+=">>  AcutuatorModuls:\n";
  for (int i = 0; i < AcutuatorModuls.size(); ++i)
  {
    ret+=AcutuatorModuls.get(i)->ShowModul()+"\n";
  }
  return ret;
}

void Block::AddModul(byte address, byte subaddress)
{
  switch (address) {
    case 1://AirModul
      SensorModules.add(new AirModul(subaddress));
      break;
    case 2://WaterModul
      SensorModules.add(new WaterModul(subaddress));
      break;
    case 3://PowerModul
      AcutuatorModuls.add(new PowerModul(subaddress));
      break;
    case 4://FanModul
      AcutuatorModuls.add(new FanModul(subaddress));
      break;
    case 5://LightModul
      AcutuatorModuls.add(new LightModul(subaddress));
      break;
      case 6://PumpModul
      AcutuatorModuls.add(new PumpModul(subaddress));
      break;
      case 7://DoserModul
      //AcutuatorModuls.add(new LightModul(subaddress));
      break;
    default:

      break;
  }
}

AcutuatorModul* Block::FindAcutuatorModul(byte address, byte subaddress)
{
  for (int i = 0; i < AcutuatorModuls.size(); ++i)
  {
    if (AcutuatorModuls.get(i)->Get_Address() == address && AcutuatorModuls.get(i)->Get_Subaddress() == subaddress)
    {
      return AcutuatorModuls.get(i);
    }
  }
  return NULL;
}
