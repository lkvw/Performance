/*
 *  // xxx Black Code
 *  Red Code
*/

// 检索是否存在符合某个条件的记录
GSPTable oResourceDetail = bidRes.asTable(pfnResourceDetail);
bool bGBCCompare = false;
if (pBidService && pBidService->isCooperateMode() && oResourceDetail.recordCount() > 0)
{
    // GSPRecordList oRecList = oResourceDetail.createRecordList("Quantity <> 0");
    // bGBCCompare = oRecList.count() > 0;
    /* Change To : */
    GSPRecord oRecord = oResourceDetail.locateEx(GString("Quantity <> 0"));
    if (NULL != oRecord)
    {
        bGBCCompare = true;
    }
}
