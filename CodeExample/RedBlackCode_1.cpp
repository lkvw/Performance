/*
 *  // xxx Black Code
 *  Red Code
*/

// 检索是否存在符合某个条件的记录
GSPTable oResourceDetail = bidRes.asTable(pfnResourceDetail);
bool bGBCCompare = false;
if (pBidService && pBidService->isCooperateMode() && oResourceDetail.recordCount() > 0)
{
    // Quantity == 0 意味着材料没有被引用，或者子目工程量为0，此时标段上的这条材料是没有意义的，无需比较
    // GSPRecordList oRecList = oResourceDetail.createRecordList("Quantity <> 0");
    // bGBCCompare = oRecList.count() > 0;
    /* Change To : */
    GSPRecord oRecord = oResourceDetail.locateEx(GString("Quantity <> 0"));
    if (NULL != oRecord)
    {
        bGBCCompare = true;
    }
}
