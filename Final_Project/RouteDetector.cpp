/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "RouteDetector.hpp"
#include "Millis.hpp"
#include "SevenSegment.hpp"

extern Millis millis;
extern SevenSegment sevensegment;

void RouteDetector::initial() {}
void RouteDetector::update_status()
{
    uint8_t new_status_value = 0;
    if(sensor_l->target_detected()) { new_status_value += 1; }
    if(sensor_c->target_detected()) { new_status_value += 2; }
    if(sensor_r->target_detected()) { new_status_value += 4; }
    /* seven segment debug (which sensor detected) */
    /*
    switch(new_status_value)
    {
        case 0:
        {
            sevensegment.print(SevenSegmentGraph::number_0);
            break;
        }
        case 1:
        {
            sevensegment.print(SevenSegmentGraph::number_1);
            break;
        }
        case 2:
        {
            sevensegment.print(SevenSegmentGraph::number_2);
            break;
        }
        case 3:
        {
            sevensegment.print(SevenSegmentGraph::number_3);
            break;
        }
        case 4:
        {
            sevensegment.print(SevenSegmentGraph::number_4);
            break;
        }
        case 5:
        {
            sevensegment.print(SevenSegmentGraph::number_5);
            break;
        }
        case 6:
        {
            sevensegment.print(SevenSegmentGraph::number_6);
            break;
        }
    }
    */

    RouteStatusType new_status = RouteStatusType::invalid;

    /* only two sensors */
    /*
    if(sensor_l->target_detected() && sensor_r->target_detected())
        new_status = RouteStatusType::center_on_line;
    else if(sensor_l->target_detected())
        new_status = RouteStatusType::llleft_on_line;
    else if(sensor_r->target_detected())
        new_status = RouteStatusType::rright_on_line;
    else
        new_status = RouteStatusType::center_on_line;
    */


    /* simple Version */
    /*
    if(sensor_c->target_detected())
    {
        if(sensor_l->target_detected() && sensor_r->target_detected())
            new_status = RouteStatusType::center_on_line;
        else if(sensor_l->target_detected())
            new_status = RouteStatusType::llleft_unknown;
        else if(sensor_r->target_detected())
            new_status = RouteStatusType::rright_unknown;
        else
            new_status = RouteStatusType::center_on_line;
    }
    else
    {
        if(sensor_l->target_detected() && sensor_r->target_detected())
            new_status = RouteStatusType::invalid;
        else if(sensor_l->target_detected())
            new_status = RouteStatusType::llleft_on_line;
        else if(sensor_r->target_detected())
            new_status = RouteStatusType::rright_on_line;
    }
    */


    /* version 1 */
    if(sensor_l->target_detected()) { new_status_value += 1; }
    if(sensor_c->target_detected()) { new_status_value += 2; }
    if(sensor_r->target_detected()) { new_status_value += 4; }

    if(new_status_value == 0)
    {
        if(current_status == RouteStatusType::llleft_unknown || current_status == RouteStatusType::center_unknown || current_status == RouteStatusType::rright_unknown)
        {
            new_status = current_status;
        }
        else if(current_status == RouteStatusType::llleft_on_line) { new_status = RouteStatusType::llleft_unknown; }
        else if(current_status == RouteStatusType::center_on_line) { new_status = RouteStatusType::center_unknown; }
        else if(current_status == RouteStatusType::rright_on_line) { new_status = RouteStatusType::rright_unknown; }
    }
    else if(new_status_value == 1) { new_status = RouteStatusType::llleft_on_line; }
    else if(new_status_value == 2) { new_status = RouteStatusType::center_on_line; }
    else if(new_status_value == 4) { new_status = RouteStatusType::rright_on_line; }

    /* seven segment debug (show status) */
    switch(new_status)
    {
        case RouteStatusType::center_on_line:
        {
            sevensegment.print(SevenSegmentGraph::number_2);
            break;
        }
        case RouteStatusType::llleft_on_line:
        {
            sevensegment.print(SevenSegmentGraph::number_1);
            break;
        }
        case RouteStatusType::center_unknown:
        {
            sevensegment.print(SevenSegmentGraph::number_5);
            break;
        }
        case RouteStatusType::rright_unknown:
        {
            sevensegment.print(SevenSegmentGraph::number_6);
            break;
        }
        case RouteStatusType::llleft_unknown:
        {
            sevensegment.print(SevenSegmentGraph::number_4);
            break;
        }
        case RouteStatusType::rright_on_line:
        {
            sevensegment.print(SevenSegmentGraph::number_3);
            break;
        }
        case RouteStatusType::invalid:
        {
            sevensegment.print(SevenSegmentGraph::number_7);
            break;
        }
        default:
        {
            break;
        }
    }

    /* change state */
    if(new_status != current_status)
    {
        last_change_status_time = millis.get();
        last_status = current_status;
        current_status = new_status;
    }
}
RouteStatusType RouteDetector::get_current_status() const { return current_status; }
RouteStatusType RouteDetector::get_last_status() const { return last_status; }
unsigned long RouteDetector::get_last_change_status_time() const { return last_change_status_time; }

