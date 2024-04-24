//
// Created by nolla on 2023/10/15.
//

#ifndef DATA_STRUCTURE_COURSE_MYALGORITHM_H
#define DATA_STRUCTURE_COURSE_MYALGORITHM_H

//第一个(大于等于value)
//第一个使得cmp为false的数
template<class iterator,class valType>
iterator myLower_bound(iterator start,iterator end, const valType& value)
{
    int l=0,r=end-start;
    int mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(*(start+mid)<value)
            l=mid+1;
        else
            r=mid;
    }
    return start+l;
}
template<class iterator,class valType,class compare>
iterator myLower_bound(iterator start, iterator end, const valType& value,compare cmp)
{
    int l=0,r=end-start;
    int mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(cmp(*(start+mid),value))
            l=mid+1;
        else
            r=mid;
    }
    return start+l;
}
//第一个(大于value)
//第一个使得cmp为true的数
template<class iterator,class valType>
iterator myUpper_bound(iterator start,iterator end,const valType& value)
{
    int l=0,r=end-start;
    int mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(value<*(start+mid))
            r=mid;
        else
            l=mid+1;
    }
    return start+l;
}
template<class iterator,class valType,class compare>
iterator myUpper_bound(iterator start,iterator end,const valType& value,compare cmp)
{
    int l=0,r=end-start;
    int mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(cmp(value,*(start+mid)))
            r=mid;
        else
            l=mid+1;
    }
    return start+l;
}
//upper_bound
bool upperDefaultCmp(int value,int mid){return value<mid;};
//lower_bound
bool lowerDefaultCmp(int mid,int value){return mid<value;};


#endif //DATA_STRUCTURE_COURSE_MYALGORITHM_H
