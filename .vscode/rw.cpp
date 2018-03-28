 if (m_DebugOn) {
        ostringstream str;
        str << msg.instrument().symbol() << ": "<< msg.bar();
        logger().LogToClient(LOGLEVEL_DEBUG, str.str().c_str());
     }

    // update our bars collection
    m_bars[&msg.instrument()] = msg.bar();
//zhaochao not very sure     
	m_rollingWindow.push_back(m_bar[].close());

        if (!m_rollingWindow.full())
        return;

	for(i=0;i<10;i++)
	{
		m_return[i]=(m_rollingWindow[i+1]-m_rollingWindow[i])/m_rollingWindow[i];
	}
	
    double sum=0;//总和  
    double avg;//平均值  
    for(i=0;i<9;i++)  
    {  
        sum+=m_return[i];//求总和  
    }  
    avg=sum/10;//计算平均值  
    
    double std=0;  
    double Spow=0;  
    for(i=0;i<9;i++)  
    {  
        Spow+=(m_return[i]-avg)*(m_return[i]-avg);//平方累加  
    }  
	m_std=sqrt(Spow/9);
    
    if (m_return[9] > m_average+0.5*m_std) {
        m_spState.unitsDesired = 50000/m_bar.colse();//if we want to use 50% of our current capital rather than the 50% of initial capital, 
	    //we can change 50000 into 0.5*portfolio().capital(BTC_USD)
    } else if (m_average-0.5*m_std<m_return[9]< m_average+0.5*m_std) {
        m_spState.unitsDesired = 25000/m_bar.colse();
    } else {
        m_spState.unitsDesired = 0;
    }
	double unitsNeeded = m_spState.unitsDesired - portfolio().position(BTC_USD);
	portfolio().capital(BTC_USD)=portfolio().capital(BTC_USD)-unitsNeeded*m_bar.close();
	if (portfolio().capital(BTC_USD)>50000)
	{
	if (unitsNeeded > 0) 
	{
        SendBuyOrder(BTC_USD, unitsNeeded);
        } 
	}
	else if (portfolio().capital(BTC_USD)>25000)
	{
		if (m_average-0.5*m_std<m_return[9] < m_average+0.5*m_std)
		SendBuyOrder(BTC_USD, unitsNeeded);
		else if (m_return[9]> m_average+0.5*m_std)
	    SendBuyOrder(BTC_USD,portfolio().capital(BTC_USD)/m_bar.colse());
		else
        SendBuyOrder(BTC_USD, 0);
	}
	else
	{
		SendBuyOrder(BTC_USD, 0);
	}
}
//No drawdown part can be added simply by use m_return[9]-m_return[8] and certain threshold
//Seems when prices increase to a certain level, we should make a decision whether to long more or sell some
//add variable: capital(portfolio().capital(BTC_USD)),return(m_return can be define at the beginning) need to figure out their names or create them
//portfolio().position(BTC_USD) this name need to be the same as previous
