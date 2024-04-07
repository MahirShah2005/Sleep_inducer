void music(vector<Dorm>& dormslist)
{
    for(Dorm& dorm : dormslist)
    {
cout << "Playing sleep inducing music in "<< dorm.getName() <<endl;
cout << "Number of inmates: " << dorm.getInmates().size() << endl;

for(Inmate* inmate: dorm.getInmates()){
    if(!inmate -> giveAsleep()){
        cout << "Playing music for inmates" << inmate->inName()<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(inmate->getTimeToFallAsleep()));
        inmate->setSleepstatus(true);
        cout<<inmate->inName()<<"fell asleep. Deactivating earpod"<<endl;
    }
}
    }
}